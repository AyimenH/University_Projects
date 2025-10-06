import app from './app.mjs'

app.listen(process.env.PORT || 3001, () => {
    console.log('server running')
})