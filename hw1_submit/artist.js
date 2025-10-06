const artists = require('../models/artistModel')
const express = require('express')
const router = express.Router()

let uniqueID = 0

// Add a new artist
router.post('/', (req, res) => {
    if (!req.body.id, !req.body.name || !req.body.biography) {
        return res.status(400).send('Missing name or biography')
    }

    const newArtist = {
        id: uniqueID++,
        name: req.body.name,
        biography: req.body.biography
    }

    artists.push(newArtist)

    res.status(201).json(newArtist)
})

// List all artists
router.get('/', (req, res) => {
    res.status(200).json(artists)
})

// Update a specific artist's name and biography
router.patch('/:id', (req, res) => {
    const id = parseInt(req.params.id)
    const newName = req.body.name
    const newBiography = req.body.biography

    const matchArtist = artists.find(artist => artist.id === id)

    if (!matchArtist) {
        return res.status(404).send('Artist not found')
    }

    if (newName !== undefined) {
        matchArtist.name = newName
    }
    if (newBiography !== undefined) {
        matchArtist.biography = newBiography
    }

    res.status(200).json(matchArtist)
})

module.exports = router