import React, { useState } from 'react';

const TCP = ({ packet }: { packet: any }) => {
  const [isOpen, setIsOpen] = useState(false);
  const toggleOpen = () => setIsOpen(!isOpen);

  const flags = packet.flags;
  const flagNames : { [key: number]: string } = {
    0x01: 'Finish (FIN)',
    0x02: 'Synchronize (SYN)',
    0x04: 'Reset (RST)',
    0x08: 'Push (PSH)',
    0x10: 'Acknowledgment (ACK)',
    0x20: 'Urgent (URG)',
    0x40: 'ECN-Echo (ECE)',
    0x80: 'Congestion Window Reduced (CWR)'
  };

  const parsedFlags = Object.keys(flagNames)
    .filter(flag => flags & parseInt(flag))
    .map(flag => flagNames[parseInt(flag)]);

  const portNames: { [key: number]: string } = {
    80: 'HTTP',
    443: 'HTTPS'
  };

  const modifiedPacket = { 
    ...packet, 
    flags: parsedFlags,
    sourcePort: `${packet.sourcePort} (${portNames[packet.sourcePort] || 'Unknown'})`,
    destinationPort: `${packet.destinationPort} (${portNames[packet.destinationPort] || 'Unknown'})`,
    dataOffset: `${packet.dataOffset} (${packet.dataOffset * 4} bytes)`
  };

  return (
    <div className="border p-4 rounded-lg shadow-md">
      <div onClick={toggleOpen} className="cursor-pointer font-bold text-lg">
        <strong>TCP Layer</strong>
      </div>
      {isOpen && (
        <pre className="mt-2 p-2 rounded">{JSON.stringify(modifiedPacket, null, 2)}</pre>
      )}
    </div>
  );
};

export default TCP;