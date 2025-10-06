const mongoose = require('mongoose')
const AutoIncrement = require('mongoose-sequence')(mongoose)

const playlistSchema = new mongoose.Schema({
    playlistId: { type: Number, unique: true },
    name: { type: String, required: true },
    isPublic: { type: Boolean, default: false },
    tracks: [{ type: String }],
    owner: { type: String, required: true },
})

// to allow playlistId to auto-increment and be saved to the database
playlistSchema.plugin(AutoIncrement, { inc_field: 'playlistId' })

module.exports = mongoose.model('Playlist', playlistSchema)
