const express = require('express')
const router = express.Router()
const Playlist = require('../models/playlistModel')
const { requiresAuth } = require('express-openid-connect')

//  Create a new playlist. A playlist consists of a name, a flag indicating whether the playlist 
// is private or public, and an ordered list of album tracks. You may choose whether the playlist 
// can start empty or if the user must include one or more tracks as part of creation.
router.post('/', requiresAuth(), async (req, res) => {
  try {
    const { name, isPublic, tracks } = req.body
    const userId = req.oidc.user.sub

    const existingPlaylist = await Playlist.findOne({ name, owner: userId })

    if (existingPlaylist) {
      return res.status(409).json({ error: 'Playlist with this name already exists' })
    }

    const playlist = new Playlist({
      name,
      isPublic: isPublic || false,
      tracks: tracks || [],
      owner: userId,
    })

    await playlist.save()
    res.status(201).json(playlist)
  } 
  
  catch (error) {
    console.error('Error creating playlist:', error.message)
    res.status(500).json({ error: 'Failed to create playlist' })
  }
})

// Add tracks within a playlist. Users can only do this to playlists they created.
router.post('/:playlistId/tracks', requiresAuth(), async (req, res) => {
  try {
    const playlist = await Playlist.findOne({ playlistId: req.params.playlistId })

    if (!playlist) return res.status(404).json({ error: 'Playlist not found' })

    if (playlist.owner !== req.oidc.user.sub) {
      return res.status(403).json({ error: 'Unauthorized: You do not own this playlist' })
    }

    const { trackUrl, position } = req.body

    if (!trackUrl.startsWith('http://localhost:3000/albums/')) {
      return res.status(400).json({ error: 'Invalid track URL format' })
    }

    if (playlist.tracks.includes(trackUrl)) {
      return res.status(409).json({ error: 'Track is already in the playlist' })
    }

    if (position !== undefined && (position < 0 || position > playlist.tracks.length)) {
      return res.status(400).json({ error: 'Invalid position' })
    }

    if (position !== undefined) {
      playlist.tracks.splice(position, 0, trackUrl)
    } 
    
    else {
      playlist.tracks.push(trackUrl)
    }

    await playlist.save()
    res.status(201).json(playlist)
  } 
  
  catch (error) {
    console.error('Error adding track to playlist:', error.message)
    res.status(500).json({ error: 'Failed to add track to playlist' })
  }
})

// Remove tracks within a playlist. Users can only do this to playlists they created.
router.delete('/:playlistId/tracks', requiresAuth(), async (req, res) => {
  try {
    const playlist = await Playlist.findOne({ playlistId: req.params.playlistId })

    if (!playlist) return res.status(404).json({ error: 'Playlist not found' })

    if (playlist.owner !== req.oidc.user.sub) {
      return res.status(403).json({ error: 'Unauthorized: You do not own this playlist' })
    }

    const { trackUrl } = req.body

    if (!playlist.tracks.includes(trackUrl)) {
      return res.status(404).json({ error: 'Track not found in playlist' })
    }

    playlist.tracks = playlist.tracks.filter(url => url !== trackUrl)
    await playlist.save()

    res.json(playlist)
  } 
  
  catch (error) {
    console.error('Error removing track from playlist:', error.message)
    res.status(500).json({ error: 'Failed to remove track from playlist' })
  }
})

// Reorder tracks within a playlist. Users can only do this to playlists they created.
router.put('/:playlistId/tracks/reorder', requiresAuth(), async (req, res) => {
  try {
    const playlist = await Playlist.findOne({ playlistId: req.params.playlistId })

    if (!playlist) return res.status(404).json({ error: 'Playlist not found' })

    if (playlist.owner !== req.oidc.user.sub) {
      return res.status(403).json({ error: 'Unauthorized: You do not own this playlist' })
    }

    const newTrackOrder = req.body.tracks
    const existingTracks = new Set(playlist.tracks)
    const newTracksSet = new Set(newTrackOrder)
    
    if (existingTracks.size !== newTracksSet.size || ![...existingTracks].every(url => newTracksSet.has(url))) {
      return res.status(400).json({ error: 'Invalid track order: All tracks must exist in the playlist' })
    }

    playlist.tracks = newTrackOrder
    await playlist.save()

    res.json(playlist)
  } 
  
  catch (error) {
    console.error('Error reordering tracks:', error.message)
    res.status(500).json({ error: 'Failed to reorder tracks' })
  }
})

// Change the public/private flag on one of the playlists they created.
router.patch('/:playlistId', requiresAuth(), async (req, res) => {
  try {
    const playlist = await Playlist.findOne({ playlistId: req.params.playlistId })
    if (!playlist) return res.status(404).json({ error: 'Playlist not found' })

    if (playlist.owner !== req.oidc.user.sub) {
      return res.status(403).json({ error: 'Unauthorized: You do not own this playlist' })
    }

    playlist.isPublic = req.body.isPublic
    await playlist.save()

    res.json(playlist)
  } 
  
  catch (error) {
    console.error('Error updating playlist:', error.message)
    res.status(500).json({ error: 'Failed to update playlist' })
  }
})

// List all public playlists. 
router.get('/public', async (req, res) => {
  try {
    const playlists = await Playlist.find({ isPublic: true })

    if (!playlists.length) {
      return res.status(404).json({ error: 'No public playlists found' })
    }

    res.json(playlists)
  } 
  
  catch (error) {
    console.error('Error fetching public playlists:', error.message)
    res.status(500).json({ error: 'Failed to retrieve playlists' })
  }
})

// List all of their own playlists.
router.get('/me', requiresAuth(), async (req, res) => {
  try {
    const playlists = await Playlist.find({ owner: req.oidc.user.sub })

    if (!playlists.length) {
      return res.status(404).json({ error: 'You have no playlists' })
    }

    res.json(playlists)
  } 
  
  catch (error) {
    console.error('Error fetching user playlists:', error.message)
    res.status(500).json({ error: 'Failed to retrieve playlists' })
  }
})

module.exports = router
