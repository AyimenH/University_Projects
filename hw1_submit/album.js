const albums = require('../models/albumModel')
const express = require('express')
const router = express.Router()

let uniqueID = 0;

// list all albums
router.get('/', (req, res) => {
    res.status(200).json(albums)
})

// Get the details all of the tracks for a specific album
router.get('/:id', (req, res) => {
    const id = parseInt(req.params.id)
    const matchAlbum = albums.find(album => album.id === id)

    if (matchAlbum) {
        res.status(200).json(matchAlbum)
    }
    else {
        res.status(404).send({ error: "Album not found" })
    }
})

// Get the details all of the tracks for a specific album
router.get('/:id/tracks', (req, res) => {
    const id = parseInt(req.params.id)
    const matchAlbum = albums.find(album => album.id === id)

    if (!matchAlbum) {
        res.status(404).send({ error: "Album not found" })
    }

    if (matchAlbum.tracks && matchAlbum.tracks.length > 0) {
        res.status(200).json(matchAlbum.tracks)
    }

    res.status(404).send({ error: "Tracks not found" })
})

// Add a new album
router.post('/', (req, res) => {
    if (!req.body.name || !req.body.year || !req.body.genre || !req.body.tracks) {
        res.status(400).send({ error: "Missing required fields" })
    }

    if(!Array.isArray(req.body.tracks)) {
        res.status(400).send({ error: "Tracks should be an array" })
    }

    const newAlbum = {
        id: uniqueID++,
        name: req.body.name,
        year: req.body.year,
        genre: req.body.genre,
        tracks: req.body.tracks
    }

    albums.push(newAlbum)

    res.status(201).json(newAlbum)
})

// Add a new track to a specific album
router.post('/:id/tracks', (req, res) => {
    const id = parseInt(req.params.id)
    const albumIndex = albums.find(album => album.id === id)

    if (albumIndex === -1) {
        res.status(404).send({ error: "Album not found" })
    }

    const newTrack = req.body

    if (!newTrack.trackNumber || !newTrack.title || !newTrack.duration || !newTrack.primaryArtist) {
        res.status(400).send({ error: "Missing required fields" })
    }

    albums[albumIndex].tracks.push(newTrack)

    res.status(201).json(newTrack)
})

// Delete a specific album (and all of its associated tracks)
router.delete('/:id', (req, res) => {
    const id = parseInt(req.params.id)
    const albumIndex = albums.findIndex(album => album.id === id)

    if (albumIndex === -1) {
        res.status(404).send({ error: "Album not found" })
    }

    const deletedAlbum = albums.splice(albumIndex, 1)

    res.status(200).json("Album deleted")
})

// Delete a specific track
router.delete('/:id/tracks/:trackNumber', (req, res) => {
    const id = parseInt(req.params.id)
    const trackNumber = parseInt(req.params.trackNumber)

    const albumIndex = albums.findIndex(album => album.id === id)

    if (albumIndex === -1) {
        res.status(404).send({ error: "Album not found" })
    }

    const trackIndex = albums[albumIndex].tracks.findIndex(track => track.trackNumber === trackNumber)

    if (trackIndex === -1) {
        res.status(404).send({ error: "Track not found" })
    }

    albums[albumIndex].tracks.splice(trackIndex, 1)

    res.status(200).json("Track deleted")
})

module.exports = router