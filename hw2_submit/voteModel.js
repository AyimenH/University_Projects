const mongoose = require('mongoose')

const voteSchema = new mongoose.Schema({
    userId: { type: String, required: true },
    tagId: { type: mongoose.Schema.Types.ObjectId, ref: 'Tag', required: true },
    vote: { type: Number, enum: [1, -1], required: true }
}, { unique: ['userId', 'tagId'] })

module.exports = mongoose.model('Vote', voteSchema)