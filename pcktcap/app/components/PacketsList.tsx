import { getPackets } from '@/data/Client';
import Ethernet from './layers/Ethernet';

const PacketsList = async ({ capture }: { capture: string }) => {
  const packets = await getPackets(capture);

  if (packets.length === 0) {
    return <div className="p-5">No packets found.</div>;
  }

  const firstTimestamp = packets[0].timestamp;

  const pckt_list = packets.map((packet, index) => {
    const relativeTime = (packet.timestamp - firstTimestamp) / 1000000; // Convert microseconds to seconds
    return (
      <div key={index} className="border border-gray-300 rounded-lg mb-2 p-2 bg-black-100">
        <p>Packet {index}, time: {relativeTime.toFixed(6)} seconds</p>
        <Ethernet packet={{ ...packet, _id: packet._id.toString() }} />
      </div>
    );
  });

  return (
    <div className="p-5">
      <h2 className="text-xl font-bold mb-4">Packets</h2>
      {pckt_list}
    </div>
  );
};

export default PacketsList;