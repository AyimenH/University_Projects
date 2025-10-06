import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { FormsModule } from '@angular/forms';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-new-playlist',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './new-playlist.component.html',
  styleUrls: ['./new-playlist.component.css'],
})
export class NewPlaylistComponent {
  name: string = '';
  isChecked: boolean = false;
  error: string | null = null;

  constructor(private router: Router, private http: HttpClient) {}

  async handleSubmit(event: Event) {
    event.preventDefault();
    this.error = null;
  
    try {
      const response = await this.http.post('/playlists', {
        name: this.name,
        isPublic: this.isChecked,
      }, { responseType: 'text' }).toPromise();
  
      this.router.navigate(['/']);
    } catch (error: any) {
      this.error = error.message || 'Failed to create playlist';
    }
  }
  
}