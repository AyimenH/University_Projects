import {MongoClient} from 'mongodb'

let client;

async function getMongoClient() {
  if(!client) {
    client = new MongoClient('mongodb://127.0.0.1:27017')
    await client.connect()
  }
  return client
}

export async function getDatabase() {
  return (await getMongoClient()).db('music-ugc')
}