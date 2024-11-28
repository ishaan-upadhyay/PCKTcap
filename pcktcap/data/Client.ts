import { MongoClient } from 'mongodb';

const url = 'mongodb://localhost:27017';
const options = {};

let client: MongoClient | null = null;

const getClient = async (): Promise<MongoClient> => {
    if (!client) {
        client = new MongoClient(url, options);
        await client.connect();
    }
    return client;
};

const getCollections = async (): Promise<string[]> => {
    const client = await getClient();
    const db = client.db('PCKTcap');
    const collections = await db.listCollections().toArray();
    return collections.map(col => col.name);
};

export { getClient, getCollections };