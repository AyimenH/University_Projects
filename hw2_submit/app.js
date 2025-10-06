require('dotenv').config()

var createError = require('http-errors')
var express = require('express')
var path = require('path')
var cookieParser = require('cookie-parser')
var logger = require('morgan')

const { auth } = require('express-openid-connect')
const mongoose = require('mongoose')

var indexRouter = require('./routes/index')
var usersRouter = require('./routes/users')

const playlistRoutes = require('./routes/playlist')
const tagRoutes = require('./routes/tag')

var app = express()

mongoose.connect(process.env.MONGODB_URI)
  .then(() => console.log('Connected to MongoDB'))
  .catch(err => console.error('MongoDB connection error:', err))

const config = {
  authRequired: true,
  auth0Logout: true,
  secret: process.env.AUTH0_CLIENT_SECRET,
  baseURL: process.env.BASE_URL,
  clientID: process.env.AUTH0_CLIENT_ID,
  issuerBaseURL: process.env.AUTH0_ISSUER_BASE_URL
}

app.set('views', path.join(__dirname, 'views'))
app.set('view engine', 'jade')

app.use(logger('dev'))
app.use(express.json())
app.use(express.urlencoded({ extended: false }))
app.use(cookieParser())
app.use(express.static(path.join(__dirname, 'public')))

app.use(auth(config))

app.use('/', indexRouter)
app.use('/users', usersRouter)

app.use('/playlists', playlistRoutes)
app.use('/tags', tagRoutes)

app.use(function(req, res, next) {
  next(createError(404))
})

app.use(function(err, req, res, next) {

  res.locals.message = err.message
  res.locals.error = req.app.get('env') === 'development' ? err : {}
  
  res.status(err.status || 500)
  res.json({
    error: {
      status: err.status || 500,
      message: err.message
    }
  })
})

module.exports = app