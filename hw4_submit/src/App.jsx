import { BrowserRouter as Router, Routes, Route } from "react-router-dom"
import PlantList from "./components/PlantList"
import PlantDetails from "./components/PlantDetails"

function App() {
  return (
    <Router>
      <div className="p-4">
        <Routes>
          <Route path="/" element={<PlantList/>} />
          <Route path="/plants/:id" element={<PlantDetails/>} />
        </Routes>
      </div>
    </Router>
  )
}

export default App