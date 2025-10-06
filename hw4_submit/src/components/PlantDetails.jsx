import { useEffect, useState } from 'react'
import { useParams } from 'react-router-dom'
import './Plants.css'

const imageMap = {
  "Arugula": "https://cpsc4910sq24.s3.amazonaws.com/images/arugula.jpg",
  "Bell pepper": "https://cpsc4910sq24.s3.amazonaws.com/images/bell-pepper.jpg",
  "Butter lettuce": "https://cpsc4910sq24.s3.amazonaws.com/images/butter-lettuce.jpg",
  "Green leaf lettuce": "https://cpsc4910sq24.s3.amazonaws.com/images/green-leaf-lettuce.jpg",
  "Strawberry": "https://cpsc4910sq24.s3.amazonaws.com/images/strawberry.jpg"
}

const PlantDetails = () => {
  const { id } = useParams()
  const [plantDetails, setPlantDetails] = useState(null)
  const [harvests, setHarvests] = useState([])
  const [error, setError] = useState(null)

  useEffect(() => {
    const fetchPlantDetails = async () => {
      try {
        const plantResponse = await fetch(`https://cpsc4910sq24.s3.amazonaws.com/data/plants/${id}.json`)
        if (!plantResponse.ok) throw new Error("Can't fetch plant details")

        const plantData = await plantResponse.json()
        setPlantDetails(plantData)

        const harvestsResponse = await fetch(`https://cpsc4910sq24.s3.amazonaws.com/data/plants/${id}/harvests.json`)
        if (!harvestsResponse.ok) throw new Error("Can't fetch harvests")
            
        const harvestsData = await harvestsResponse.json()
        setHarvests(harvestsData)
      } catch (err) {
        setError(err.message)
      }
    }

    fetchPlantDetails()
  }, [id])

  if (error) {
    return <div>Error: {error}</div>
  }

  if (!plantDetails) {
    return <div>Loading...</div>
  }

  let key = plantDetails.species
  if (plantDetails.cultivar) {
    key = `${plantDetails.cultivar} ${plantDetails.species.toLowerCase()}`
  }

  const imageUrl = imageMap[key] || "https://via.placeholder.com/300"

  return (
    <div className="plant-details-container">
      <h1 id='name'>{plantDetails.name}</h1>

      <div className="plant-content">
        <div className="plant-info-detail">

          <img className="detail-plant-image" src={imageUrl} alt={plantDetails.name} />

          <p><strong>Species:</strong> {plantDetails.species}</p>
          {plantDetails.cultivar && <p><strong>Cultivar:</strong> {plantDetails.cultivar}</p>}
          <p><strong>Stage:</strong> {plantDetails.stage}</p>
        </div>

        <div className="harvest-info">
          <h2 id='name'>Harvests</h2>
          <table className="harvest-table">
            <thead>
              <tr>
                <th>Date</th>
                <th>Quantity</th>
              </tr>
            </thead>
            <tbody>
              {harvests.length > 0 ? (
                harvests.map((harvest, index) => (
                  <tr key={index} className={index % 2 === 0 ? "even-row" : ""}>
                    <td>{harvest.Date}</td>
                    <td>{harvest.Amount}</td>
                  </tr>
                ))
              ) : (
                <tr><td colSpan="2">No harvest records available</td></tr>
              )}
            </tbody>
          </table>
        </div>
      </div>
    </div>
  )
}

export default PlantDetails
