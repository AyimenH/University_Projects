import { useState, useEffect } from "react"
import { Link } from "react-router-dom"

function PlaylistList() {
  const [playlists, setPlaylists] = useState([])

  useEffect(() => {
    fetch("/playlists")
      .then((res) => res.json())
      .then((data) => setPlaylists(data))
      .catch((err) => console.error("Error fetching playlists:", err))
  }, [])

  return (
    <div>
      <h1 className="text-xl font-bold">My Playlists</h1>
      <Link to="/new" className="p-2 bg-blue-500 text-white rounded">Create New Playlist</Link>

      {playlists.length === 0 ? (
        <p>No available playlist!</p>
      ) : (
        <ul>
          {playlists.map((playlist) => (
            <li key={playlist._id} className="p-2 border rounded my-2">
              <h2 className="text-lg font-semibold">{playlist.name}</h2>
              
              <p>{playlist.isPublic ? "Public" : "Private"}</p>
              <Link 
                to={`/edit/${playlist._id}`} 
                className="text-blue-500"
                state={{ isPublic: playlist.isPublic }}
              >
                Edit
              </Link>
            </li>
          ))}
        </ul>
      )}
    </div>
  )
}

export default PlaylistList
