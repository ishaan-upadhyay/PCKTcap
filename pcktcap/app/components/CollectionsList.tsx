import { getCollections } from "../../data/Client";
import { formatDate } from "../utils/formatDate";

const CollectionsList = async () => {
  const collections = await getCollections();

  return (
    <ul className="list-disc pl-5">
      {collections.map((collection) => (
        <li key={collection} className="mb-2">
          <a href={`/${collection}`} className="text-blue-500 hover:underline">
            {formatDate(collection)}
          </a>
        </li>
      ))}
    </ul>
  );
};

export default CollectionsList;