const tracksByAlbumId = {}

export function addTrack(albumId, track) {
    const tracks = tracksByAlbumId[albumId] ??= []
    track.trackNumber = tracks.length
    tracks.push(track)
    return track.trackNumber
}

export function getTracksForAlbum(albumId) {
    return tracksByAlbumId[albumId] || []
}

export function deleteTrack(albumId, trackNumber) {
    const tracks = tracksByAlbumId[albumId]
    if(tracks) {
        tracks.splice(trackNumber, 1)
    }
}

export function deleteAllTracksForAlbum(albumId) {
    delete tracksByAlbumId[albumId]
}