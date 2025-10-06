import { BrowserRouter as Router, Routes, Route } from "react-router-dom"
import PlaylistList from "./components/PlaylistList"
import NewPlaylist from "./components/NewPlaylist"
import EditPlaylist from "./components/EditPlaylist"

function App() {
  return (
    <Router>
      <div className="p-4">
        <Routes>
          <Route path="/" element={<PlaylistList/>} />
          <Route path="/new" element={<NewPlaylist/>} />
          <Route path="/edit/:id" element={<EditPlaylist/>} />
        </Routes>
      </div>
    </Router>
  )
}

export default App