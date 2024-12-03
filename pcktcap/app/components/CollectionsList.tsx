import { getCollections } from "../../data/Client";
import { formatCollectionName } from "../utils/formatCollectionName";

const CollectionsList = async () => {
  const collections = await getCollections();

  // Sort collections in descending order of timestamp,
  // names are formatted as cap_<time_since_epoch>_<interface>
  collections.sort((a, b) => parseInt(b.split('_')[1]) - parseInt(a.split('_')[1]));

  return (
    <ul className="list-disc pl-5">
      {collections.map((collection) => (
        <li key={collection} className="mb-2">
          <a href={`/${collection}`} className="text-blue-500 hover:underline">
            {formatCollectionName(collection)}
          </a>
        </li>
      ))}
    </ul>
  );
};

export default CollectionsList;