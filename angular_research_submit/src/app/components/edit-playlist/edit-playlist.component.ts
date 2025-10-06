import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { forkJoin } from 'rxjs';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-edit-playlist',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './edit-playlist.component.html',
  styleUrls: ['./edit-playlist.component.css'],
})

export class EditPlaylistComponent implements OnInit {
  id: string | null = null;
  isChecked: boolean = false;

  albums: any[] = [];
  albumTracks: { [key: string]: any[] } = {};

  playlist: any = null;
  playlistTracks: any[] = [];

  constructor(
    private route: ActivatedRoute,
    private router: Router,
    private http: HttpClient
  ) {}

  ngOnInit() {
    this.route.paramMap.subscribe((params) => {
      this.id = params.get('id');
      this.fetchAlbumsAndTracks();
      this.fetchPlaylist();
    });
    const isPublic = history.state?.isPublic;
    this.isChecked = isPublic || false;
  }

  fetchAlbumsAndTracks() {
    this.http.get<any[]>('/albums').subscribe((albumsData) => {
      this.albums = albumsData;
      const trackRequests = albumsData.map(album =>
        this.http.get<any[]>(`/albums/${album.id}/tracks`)
      );
  
      forkJoin(trackRequests).subscribe((results) => {
        results.forEach((albumTracksData, index) => {
          this.albumTracks[this.albums[index].id] = albumTracksData;
        });

        this.fetchPlaylist();
      });
    });
  }
  

  isTrackInPlaylist(track: any, albumId: string): boolean {
    return this.playlistTracks.some(t => t.trackNumber === track.trackNumber && t.albumId == albumId);
  }  

  fetchPlaylist() {
    this.http.get<any[]>('/playlists').subscribe((playlists) => {
      const selectedPlaylist = playlists.find(
        (p) => String(p._id) === this.id
      );
      if (!selectedPlaylist) {
        console.error('Playlist not found');
        return;
      }

      this.playlist = selectedPlaylist;
      this.extractTracksFromPlaylist(selectedPlaylist.tracks || []);
    });
  }

  extractTracksFromPlaylist(trackIds: string[]) {
    let extractedTracks: any[] = [];
  
    trackIds.forEach((trackId) => {
      const parts = trackId.split('/');
      if (parts.length < 4) {
        console.error(`Invalid trackId format: ${trackId}`);
        return;
      }
  
      const albumId = parts[1];
      const trackNumber = Number(parts[3]);
  
      if (!albumId) {
        console.error(`Missing albumId for trackId: ${trackId}`);
        return;
      }
  
      const albumTracksList = this.albumTracks[albumId] || [];
      const foundTrack = albumTracksList.find((track) => track.trackNumber === trackNumber);
  
      if (foundTrack) {
        extractedTracks.push({ ...foundTrack, albumId }); 
      } else {
        console.error(`Track ${trackNumber} not found in album ${albumId}`);
      }
    });
  
    this.playlistTracks = extractedTracks;
  }
  

  handleChange(event: Event) {
    this.isChecked = (event.target as HTMLInputElement).checked;
  
    this.http.put(`/playlists/${this.id}/isPublic`, { isPublic: this.isChecked }).subscribe({
      next: () => {
      },
      error: (error) => {
        console.error('Error updating playlist public status:', error);
      }
    });
  }
  

  moveTrack(index: number, direction: number) {
    const newIndex = index + direction;
    if (newIndex < 0 || newIndex >= this.playlistTracks.length) return;

    const newOrder = [...this.playlistTracks];
    [newOrder[index], newOrder[newIndex]] = [
      newOrder[newIndex],
      newOrder[index],
    ];
    this.playlistTracks = newOrder;

    const albumId = newOrder[newIndex].albumId;
    const trackNumber = newOrder[newIndex].trackNumber;
    const trackId = `albums/${albumId}/tracks/${trackNumber}`;

    this.http
      .patch(`/playlists/${this.id}/tracks`, {
        trackId,
        position: newIndex,
      })
      .subscribe({
        next: () => {
        },
        error: (error) => {
          console.error('Error updating track order:', error);
        }
      });
  }

  addTrackToPlaylist(albumId: string, trackNumber: number) {

    if (this.isTrackInPlaylist({ trackNumber }, albumId)) {
      return;
    }

    const trackId = `albums/${albumId}/tracks/${trackNumber}`;

    this.http.post(`/playlists/${this.id}/tracks`, { trackId }).subscribe({
      next: (response: any) => {
        const newTrack = (this.albumTracks[albumId] || []).find(
          (track) => track.trackNumber === trackNumber
        );
        if (newTrack) {
          this.playlistTracks.push({ ...newTrack, albumId });
        }
      },
      error: (error) => {
        console.error('Error adding track:', error);
      }
    });
    
  }

  removeTrackFromPlaylist(albumId: string, trackNumber: number) {
    const trackId = `albums/${albumId}/tracks/${trackNumber}`;
  
    this.http
      .delete(`/playlists/${this.id}/tracks`, { body: { trackId } })
      .subscribe({
        next: () => {
          this.playlistTracks = this.playlistTracks.filter(
            (track) =>
              track.trackNumber !== trackNumber || track.albumId !== albumId
          );
        },
        error: (error) => {
          console.error('Error removing track:', error);
        }
      });
  }

  handleDoneEditing() {
    this.router.navigate(['/']);
  }
}
