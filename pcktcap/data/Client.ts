import { MongoClient } from 'mongodb';

const url = 'mongodb://localhost:27017';
const options = {};

let client: MongoClient | null = null;

/* Return a MongoClient instance (singleton). 
 * If one does not exist, create one and connect to the database.
 */
const getClient = async (): Promise<MongoClient> => {
    if (!client) {
        client = new MongoClient(url, options);
        await client.connect();
    }
    return client;
};

/* Return a list of collection names in the database. */
const getCollections = async (): Promise<string[]> => {
    const client = await getClient();
    const db = client.db('PCKTcap');
    const collections = await db.listCollections().toArray();
    return collections.map(col => col.name);
};

/* Get packets from a collection. */
const getPackets = async (collection: string): Promise<any[]> => {
    const client = await getClient();
    const db = client.db('PCKTcap');
    const coll = db.collection(collection);
    const packets = await coll.find().sort({ timestamp: 1 }).toArray();
    return packets;
};

export { getClient, getCollections, getPackets };