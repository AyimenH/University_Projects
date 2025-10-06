import { Routes } from '@angular/router';
import { PlaylistListComponent } from './components/playlist-list/playlist-list.component';
import { NewPlaylistComponent } from './components/new-playlist/new-playlist.component';
import { EditPlaylistComponent } from './components/edit-playlist/edit-playlist.component';

export const routes: Routes = [
    { path: '', component: PlaylistListComponent },
    { path: 'new', component: NewPlaylistComponent },
    { path: 'edit/:id', component: EditPlaylistComponent }
];