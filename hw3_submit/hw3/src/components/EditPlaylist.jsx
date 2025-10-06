import { useState, useEffect } from "react"
import { useParams, useLocation } from "react-router-dom"

function EditPlaylist() {
  const { id } = useParams()
  const location = useLocation()
  const { isPublic } = location.state || {}
  const [checked, setChecked] = useState(isPublic || false)
  const [playlist, setPlaylist] = useState(null)
  const [albums, setAlbums] = useState([])
  const [albumTracks, setAlbumTracks] = useState({})
  const [playlistTracks, setPlaylistTracks] = useState([])

  useEffect(() => {
    const fetchAlbumsAndTracks = async () => {
      try {
        const albumsRes = await fetch("/albums")
        const albumsData = await albumsRes.json()
        setAlbums(albumsData)

        let tracksMap = {}

        for (const album of albumsData) {
          const tracksRes = await fetch(`/albums/${album.id}/tracks`)
          const albumTracksData = await tracksRes.json()
          tracksMap[album.id] = albumTracksData
        }
        setAlbumTracks(tracksMap)

      } catch (err) {
        console.error("Error fetching albums or tracks:", err)
      }
    }

    fetchAlbumsAndTracks()
  }, [])

  useEffect(() => {
    const fetchPlaylist = async () => {
      try {
        const playlistsRes = await fetch("/playlists")
        const playlists = await playlistsRes.json()

        const selectedPlaylist = playlists.find((p) => String(p._id) === id)
        if (!selectedPlaylist) {
          console.error("Playlist not found")
          return
        }

        setPlaylist(selectedPlaylist)
        extractTracksFromPlaylist(selectedPlaylist.tracks || [])
      } catch (err) {
        console.error("Error fetching playlist:", err)
      }
    }

    fetchPlaylist()
  }, [id, albumTracks])

  const extractTracksFromPlaylist = (trackIds) => {
    let extractedTracks = []

    trackIds.forEach((trackId) => {
      const [_, albumId, __, trackNumber] = trackId.split("/")
      const albumTracksList = albumTracks[albumId] || []
      const foundTrack = albumTracksList.find((track) => track.trackNumber === Number(trackNumber))

      if (foundTrack) {
        extractedTracks.push(foundTrack)
      }
    })

    setPlaylistTracks(extractedTracks)
  }

  const handleChange = () => {
    setChecked(!checked)
  }

  const Checkbox = ({ label, value, onChange }) => {
    return (
      <label>
        <input type="checkbox" checked={value} onChange={onChange} />
        {label}
      </label>
    );
  };

  const moveTrack = async (index, direction) => {
    const newIndex = index + direction
    if (newIndex < 0 || newIndex >= playlistTracks.length) return

    const newOrder = [...playlistTracks];
    [newOrder[index], newOrder[newIndex]] = [newOrder[newIndex], newOrder[index]]
    setPlaylistTracks(newOrder)

    const albumId = newOrder[newIndex].albumId
    const trackNumber = newOrder[newIndex].trackNumber
    const trackId = `albums/${albumId}/tracks/${trackNumber}`

    try {
      await fetch(`/playlists/${id}/tracks`, {
        method: "PATCH",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ trackId, position: newIndex })
      })

    } catch (error) {
      console.error("Error updating track order:", error)
    }
  }

  const addTrackToPlaylist = async (albumId, trackNumber) => {
    const trackId = `albums/${albumId}/tracks/${trackNumber}`

    try {
      const response = await fetch(`/playlists/${id}/tracks`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ trackId }),
      })

      if (response.ok) {
        const newTrack = (albumTracks[albumId] || []).find(track => track.trackNumber === Number(trackNumber));
        if (newTrack) {
          setPlaylistTracks(prevTracks => [...prevTracks, newTrack]);
        }
      } else {
        console.error("Failed to add track");
      }
    } catch (error) {
      console.error("Error adding track:", error);
    }
  };

  const removeTrackFromPlaylist = async (albumId, trackNumber) => {
    const trackId = `albums/${albumId}/tracks/${trackNumber}`;

    try {
      const response = await fetch(`/playlists/${id}/tracks`, {
        method: "DELETE",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ trackId }),
      });

      if (response.ok) {
        setPlaylistTracks(prevTracks => prevTracks.filter(track => track.trackNumber !== Number(trackNumber) || track.albumId !== albumId));
      } else {
        console.error("Failed to remove track");
      }
    } catch (error) {
      console.error("Error removing track:", error);
    }
  };

  return (
    <div className="bg-black text-white">
      <div className="p-4">
        <h1 className="text-4xl font-bold mb-4">Edit Playlist</h1>
        <Checkbox label="Public" value={checked} onChange={handleChange} />

        {playlist ? <h2 className="text-2xl mt-2 mb-4">{playlist.name}</h2> : <p>Playlist loading...</p>}

        <div className="flex flex-row space-x-8">
          {/* Left side - Playlist Tracks */}
          <div className="w-1/2">
            <h2 className="text-2xl mb-4">Playlist Tracks</h2>
            {playlistTracks.length === 0 ? (
              <p>Playlist Empty</p>
            ) : (
              <ul className="space-y-4">
                {playlistTracks.map((track, index) => (
                  <li key={`${track.albumId}-${track.trackNumber}`} className="list-disc ml-5">
                    <p className="text-lg">{track.title}</p>
                    <p>Duration: {track.duration}</p>
                    <p>Artist: {track.primaryArtist}</p>
                    
                    <div className="mt-2 mb-2">
                      <button 
                        onClick={() => moveTrack(index, -1)} 
                        disabled={index === 0}
                        className="bg-gray-800 px-4 py-2 mr-1"
                      >
                        ↑
                      </button>
                      <button 
                        onClick={() => moveTrack(index, 1)} 
                        disabled={index === playlistTracks.length - 1}
                        className="bg-gray-800 px-4 py-2 mr-1"
                      >
                        ↓
                      </button>
                      <button 
                        onClick={() => removeTrackFromPlaylist(track.albumId, track.trackNumber)} 
                        className="bg-gray-800 px-4 py-2"
                      >
                        Remove Track
                      </button>
                    </div>
                  </li>
                ))}
              </ul>
            )}
          </div>

          {/* Right side - Available Albums */}
          <div className="w-1/2">
            <h2 className="text-2xl mb-4">Available Albums</h2>
            {albums.length === 0 ? (
              <p>No albums available.</p>
            ) : (
              <div>
                {albums.map((album) => (
                  <div key={album.id} className="mb-6">
                    <h3 className="text-xl font-bold">{album.name}</h3>
                    <p>Genre: {album.genre}</p>
                    <p>Year Released: {album.yearReleased}</p>

                    <ul className="mt-2">
                      {(albumTracks[album.id] || []).map((track) => {
                        const isTrackInPlaylist = playlistTracks.some(
                          (t) => t.trackNumber === track.trackNumber && t.albumId === album.id
                        );
                        return (
                          <li key={track.trackNumber} className="list-disc ml-5 mt-2">
                            <p>{track.title}</p>
                            <p>Duration: {track.duration}</p>
                            <p>Artist: {track.primaryArtist}</p>

                            <button
                              onClick={() => addTrackToPlaylist(album.id, track.trackNumber)}
                              className="mt-2 mb-2 bg-gray-800 px-4 py-2"
                              disabled={isTrackInPlaylist}
                            >
                              {isTrackInPlaylist ? "✓" : "Add Track"}
                            </button>
                          </li>
                        );
                      })}
                    </ul>
                  </div>
                ))}
              </div>
            )}
          </div>
        </div>
      </div>
    </div>
  );
}

export default EditPlaylist;