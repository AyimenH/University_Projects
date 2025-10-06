const concerts = require('../models/concertModel')
const express = require('express')
const router = express.Router()

// List all concerts within a time range (min and max start time)
router.get('/', (req, res) => {
    const minDate = req.query.minDate
    const maxDate = req.query.maxDate

    if (!minDate || !maxDate) {
        res.status(400).send('Please provide minDate and maxDate')
    }

    const min = new Date(minDate)
    const max = new Date(maxDate)

    if (isNaN(min) || isNaN(max)) {
        res.status(400).send('Invalid date format, please use YYYY-MM-DD')
    }

    const filterConcerts = concerts.filter(concert => {
        const concertDate = new Date(concert.date)
        return concertDate >= min && concertDate <= max
    })

    res.json(filterConcerts)
})

// Change the start date/time of a specific concert
router.patch('/:id', (req, res) => {
    const id = parseInt(req.params.id)
    const newDate = req.body.date

    const matchConcert = concerts.find(concert => concert.id === id)

    if (!matchConcert) {
        res.status(404).send('Concert not found')
    }

    if (newDate !== undefined) {
        matchConcert.date = newDate
    }

    res.status(200).json(matchConcert)
})

module.exports = router
