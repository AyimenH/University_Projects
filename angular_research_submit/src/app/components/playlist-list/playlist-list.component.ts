import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Router } from '@angular/router';
import { CommonModule } from '@angular/common';
import { RouterModule } from '@angular/router';

interface Playlist {
  _id: string;
  name: string;
  isPublic: boolean;
}

@Component({
  selector: 'app-playlist-list',
  standalone: true,  
  imports: [CommonModule, RouterModule],  
  templateUrl: './playlist-list.component.html',
  styleUrls: ['./playlist-list.component.css']
  
})
export class PlaylistListComponent implements OnInit {
  playlists: Playlist[] = [];

  constructor(private http: HttpClient, private router: Router) {}

  ngOnInit(): void {
    this.http.get<Playlist[]>('/playlists').subscribe({
      next: (data) => (this.playlists = data),
      error: (err) => console.error('Error fetching playlists:', err)
    });
  }

  navigateToEdit(playlist: Playlist): void {
    this.router.navigate([`/edit/${playlist._id}`], { state: { isPublic: playlist.isPublic } });
  }
}