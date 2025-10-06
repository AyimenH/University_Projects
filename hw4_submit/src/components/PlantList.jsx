import { useEffect, useState } from 'react'
import './Plants.css'

const PlantList = () => {
  const imageMap = {
    "arugula": "https://cpsc4910sq24.s3.amazonaws.com/images/arugula.jpg",
    "bell pepper": "https://cpsc4910sq24.s3.amazonaws.com/images/bell-pepper.jpg",
    "butter lettuce": "https://cpsc4910sq24.s3.amazonaws.com/images/butter-lettuce.jpg",
    "green leaf lettuce": "https://cpsc4910sq24.s3.amazonaws.com/images/green-leaf-lettuce.jpg",
    "strawberry": "https://cpsc4910sq24.s3.amazonaws.com/images/strawberry.jpg"
  }

  const [plants, setPlants] = useState([])

  useEffect(() => {
    fetch("https://cpsc4910sq24.s3.amazonaws.com/data/plants.json")
      .then((res) => res.json())
      .then((data) => setPlants(data))
      .catch((err) => console.error("Can't fetch plants: ", err))
  }, [])

  return (
    <div className="plant-list">
      <h1 id="name">Plant Palace</h1>

      <details className="plant-details" open>
        <summary><strong>Greenhouse</strong></summary>
        <ul>
          {plants
            .filter((plant) => plant.location === "Greenhouse")
            .map((plant) => {
              const key = plant.cultivar
                ? `${plant.cultivar.toLowerCase()} ${plant.species.toLowerCase()}`
                : plant.species.toLowerCase()

              const imageUrl = imageMap[key.trim()] || "https://via.placeholder.com/150"

              return (
                <li key={plant.id} className="plant-item">
                  <img src={imageUrl} alt={plant.name} className="plant-image" />

                  <div className="plant-info">
                    <a href={`/plants/${plant.id}`}><strong>{plant.name}</strong></a>
                    <p><strong>Species: </strong>{plant.species}</p>
                    {plant.cultivar && <p><strong>Cultivar: </strong>{plant.cultivar}</p>}
                    <p><strong>Stage: </strong>{plant.stage}</p>
                  </div>
                </li>
              )
            })}
        </ul>
      </details>

      <details className="plant-details" open>
        <summary><strong>Living Room Hydroponics</strong></summary>
        <ul>
        {plants
            .filter((plant) => plant.location === "Living room hydroponics")
            .map((plant) => {
              const key = plant.cultivar
                ? `${plant.cultivar.toLowerCase()} ${plant.species.toLowerCase()}`
                : plant.species.toLowerCase()

              const imageUrl = imageMap[key.trim()] || "https://via.placeholder.com/150"

              return (
                <li key={plant.id} className="plant-item">
                  <img src={imageUrl} alt={plant.name} className="plant-image" />

                  <div className="plant-info">
                    <a href={`/plants/${plant.id}`}><strong>{plant.name}</strong></a>
                    <p><strong>Species: </strong>{plant.species}</p>
                    {plant.cultivar && <p><strong>Cultivar: </strong>{plant.cultivar}</p>}
                    <p><strong>Stage: </strong>{plant.stage}</p>
                  </div>
                </li>
              )
            })}
        </ul>
      </details>

      <details className="plant-details" open>
        <summary><strong>Front Yard</strong></summary>
        <ul>
        {plants
            .filter((plant) => plant.location === "Front yard")
            .map((plant) => {
              const key = plant.cultivar
                ? `${plant.cultivar.toLowerCase()} ${plant.species.toLowerCase()}`
                : plant.species.toLowerCase()

              const imageUrl = imageMap[key.trim()] || "https://via.placeholder.com/150"

              return (
                <li key={plant.id} className="plant-item">
                  <img src={imageUrl} alt={plant.name} className="plant-image" />

                  <div className="plant-info">
                    <a href={`/plants/${plant.id}`}><strong>{plant.name}</strong></a>
                    <p><strong>Species: </strong>{plant.species}</p>
                    {plant.cultivar && <p><strong>Cultivar: </strong>{plant.cultivar}</p>}
                    <p><strong>Stage: </strong>{plant.stage}</p>
                  </div>
                </li>
              )
            })}
        </ul>
      </details>
    </div>
  )
}

export default PlantList