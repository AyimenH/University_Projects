const express = require('express')
const router = express.Router()
const Tag = require('../models/tagModel')
const Vote = require('../models/voteModel');
const { requiresAuth } = require('express-openid-connect')


// Add a tag to a track. A tag is just a string describing the track, like "upbeat" or "funky".
router.post('/albums/:albumId/tracks/:trackNumber/tags', requiresAuth(), async (req, res) => {
  try {
    const albumId = parseInt(req.params.albumId)
    const trackNumber = parseInt(req.params.trackNumber)

    const { tag } = req.body
    
    const externalApiUrl = `http://localhost:3000/album/${albumId}`
    const response = await fetch(externalApiUrl)
    
    if (!response.ok) {
      return res.status(404).json({ error: "Album not found on external server" })
    }

    const album = await response.json()

    const track = album.tracks.find(t => t.trackNumber === trackNumber)

    if (!track) {
      return res.status(404).json({ error: "Track not found in album" })
    }

    const trackIdentifier = `${albumId}-${trackNumber}`

    let existingTag = await Tag.findOne({ trackId: trackIdentifier, tag })

    if (!existingTag) {
      existingTag = new Tag({
        trackId: trackIdentifier,
        tag,
        albumId,
        trackTitle: track.title,
      })

      await existingTag.save()
      return res.status(201).json(existingTag)
    } 
    
    if (existingTag) {
      return res.status(409).json({ 
        error: "Tag already exists for this track", 
        existingTag 
      })
    }
    
    res.json(existingTag)
  } 
  
  catch (error) {
    console.error("Error fetching album data:", error.message)
    res.status(500).json({ error: "Failed to retrieve album or track data" })
  }
})

// Upvote or downvote a tag for a specific track. Each user can only vote on a specific tag+track once.
router.put('/:trackId/tags/:tag/vote', requiresAuth(), async (req, res) => {
  try {
    const { trackId, tag } = req.params
    const { vote } = req.body

    const userId = req.oidc.user.sub

    if (![1, -1].includes(vote)) {
      return res.status(400).json({ error: 'Invalid vote. Must be 1 or -1.' })
    }

    const existingTag = await Tag.findOne({ trackId, tag })

    if (!existingTag) {
      return res.status(404).json({ error: 'Tag not found for this track' })
    }

    const existingVote = await Vote.findOne({ userId, tagId: existingTag._id })

    if (existingVote) {
      if (existingVote.vote === vote) {
        return res.status(409).json({ error: 'You have already voted this way', existingTag })
      }

      const voteChange = vote === 1 ? { upvotes: 1, downvotes: -1 } : { upvotes: -1, downvotes: 1 }
      await Tag.updateOne({ _id: existingTag._id }, { $inc: voteChange })

      existingVote.vote = vote
      await existingVote.save()
    } 
    
    else {
      const newVote = new Vote({ userId, tagId: existingTag._id, vote })
      await newVote.save()

      const voteUpdate = vote === 1 ? { upvotes: 1 } : { downvotes: 1 }
      await Tag.updateOne({ _id: existingTag._id }, { $inc: voteUpdate })
    }

    const updatedTag = await Tag.findById(existingTag._id)
    res.json(updatedTag)
  } 
  
  catch (error) {
    console.error('Error voting on tag:', error.message)
    res.status(500).json({ error: 'Failed to process vote' })
  }
})

// List all tracks with a positive number of votes for a specific tag (i.e. where |upvotes| > |downvotes|). 
router.get('/:tag/tracks', async (req, res) => {
  try {
    const { tag } = req.params

    const tags = await Tag.find({
      tag,
      $expr: { $gt: [{ $subtract: ['$upvotes', '$downvotes'] }, 0] }
    })

    if (!tags.length) {
      return res.status(404).json({ error: 'No tracks found with positive votes for this tag' })
    }

    res.json({ tracks: tags.map(t => t.trackTitle) })
  } 
  
  catch (error) {
    console.error('Error fetching tracks by tag:', error.message)
    res.status(500).json({ error: 'Failed to retrieve tracks' })
  }
})

module.exports = router