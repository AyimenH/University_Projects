import { useState } from "react"
import { useNavigate } from "react-router-dom"

function NewPlaylist() {
  const [name, setName] = useState("")
  const [checked, setChecked] = useState(false)
  const [error, setError] = useState(null)
  const navigate = useNavigate()

  const handleSubmit = async (e) => {
    e.preventDefault()
    setError(null)

    const response = await fetch("/playlists", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({
        name,
        isPublic: checked,
      }),
    })
    

    if (!response.ok) {
      const errorData = await response.json()
      throw new Error(errorData.errors?.map(err => err.msg).join(", ") || "Create playlist failed!")
    }

    navigate("/")
  }

  const handleChange = () => {
    setChecked(!checked)
  }

  return (
    <form onSubmit={handleSubmit} className="p-4 border rounded">
      <label className="block mb-2">
        Playlist Name:
        <input
          type="text"
          value={name}
          onChange={(e) => setName(e.target.value)}
          className="border p-2 w-full rounded"
          required
        />
      </label>
      <Checkbox
        label="Public"
        value={checked}
        onChange={handleChange}
      />
      <button type="submit" className="mt-2 p-2 bg-blue-500 text-white rounded">
        Create Playlist
      </button>
    </form>
  )
}

const Checkbox = ({ label, value, onChange }) => {
  return (
    <label>
      <input type="checkbox" checked={value} onChange={onChange} />
      {label}
    </label>
  )
}

export default NewPlaylist