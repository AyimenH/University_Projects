const mongoose = require('mongoose')

const tagSchema = new mongoose.Schema({
    trackId: { type: String, required: true },
    trackTitle: { type: String, required: true },
    tag: { type: String, required: true },
    upvotes: { type: Number, default: 0 },
    downvotes: { type: Number, default: 0 }
}, { unique: ['trackId', 'tag'] })

module.exports = mongoose.model('Tag', tagSchema)