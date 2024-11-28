import PacketsList from '../components/PacketsList';
import { formatDate } from '../utils/formatDate';

interface CapturePageProps {
  params: { capture: string };
}

export default async function CapturePage({ params }: CapturePageProps) {

  const p = await params;
  const cap = p.capture;
  const formattedDate = formatDate(cap);

  return (
    <div className="p-4">
      <h1 className="text-2xl font-bold mb-4">Captured at: {formattedDate}</h1>
      {cap && <PacketsList capture={cap} />}
    </div>
  );
}
