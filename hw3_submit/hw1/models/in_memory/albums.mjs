const albums = {}
let nextId = 0

export function getAlbums() {
    return Object.values(albums)
}

export function addAlbum(album) {
    const id = nextId++
    album.id = id
    albums[id] = album
    return id
}

export function getAlbumById(id) {
    return albums[id]
}

export function deleteAlbum(id) {
    delete albums[id]
}