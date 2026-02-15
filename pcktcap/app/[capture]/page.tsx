import PacketsList from '../components/PacketsList';
import { formatCollectionName } from '../utils/formatCollectionName';

interface CapturePageProps {
  params: Promise<{ capture: string }>;
}

export default async function CapturePage({ params }: CapturePageProps) {

  const p = await params;
  const cap = p.capture;
  const formattedName = formatCollectionName(cap);

  return (
    <div className="p-4">
      <h1 className="text-2xl font-bold mb-4">Captured at: {formattedName}</h1>
      {cap && <PacketsList capture={cap} />}
    </div>
  );
}
