import CollectionsList from "./components/CollectionsList";

export default function Home() {
  return (
    <div className="min-h-screen p-4">
        <h1 className="text-4xl font-bold text-center text-blue-600 mb-4">PCKTcap</h1>
        <h2 className="text-2xl font-semibold text-center text-white-600 mb-6">Captures:</h2>
        <CollectionsList />
    </div>
  );
}
