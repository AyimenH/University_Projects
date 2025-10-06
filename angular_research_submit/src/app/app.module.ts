import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppComponent } from './app.component'; 
import { EditPlaylistComponent } from './components/edit-playlist/edit-playlist.component';  
import { CommonModule } from '@angular/common';  
import { FormsModule } from '@angular/forms';  
import { RouterModule } from '@angular/router';  

@NgModule({
declarations: [
    AppComponent,           
    EditPlaylistComponent,
    
],
imports: [
    BrowserModule,          
    CommonModule,          
    FormsModule,            
    RouterModule,          
    
],
providers: [],
bootstrap: [AppComponent]
})
export class AppModule {}