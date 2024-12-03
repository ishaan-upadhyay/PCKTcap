import React, { useState } from 'react';

const ICMP = ({ packet }: { packet: any }) => {
  const [isOpen, setIsOpen] = useState(false);
  const toggleOpen = () => setIsOpen(!isOpen);

  const types: { [key: number]: string } = {
    0: 'Echo Reply',
    3: 'Destination Unreachable',
    8: 'Echo Request',
    11: 'Time Exceeded'
  };

  const codes: { [key: number]: { [key: number]: string } } = {
    0: { 0: 'No Code' },
    3: { 0: 'Net Unreachable', 
         1: 'Host Unreachable', 
         2: 'Protocol Unreachable', 
         3: 'Port Unreachable', 
         4: 'Fragmentation Needed and Don\'t Fragment was Set', 
         5: 'Source Route Failed' 
        },
    8: { 0: 'No Code' },
    11: { 0: 'Time to Live exceeded in Transit', 
          1: 'Fragment Reassembly Time Exceeded' }
  };

  const modifiedPacket = {
    ...packet,
    type: `${packet.type} (${types[packet.type] || 'Unknown'})`,
    code: `${packet.code} (${codes[packet.type]?.[packet.code] || 'Unknown'})`
  };

  return (
    <div className="border p-4 rounded-lg shadow-md">
      <div onClick={toggleOpen} className="cursor-pointer font-bold text-lg">
        <strong>ICMP Layer</strong>
      </div>
      {isOpen && (
        <pre className="mt-2 p-2 rounded">{JSON.stringify(modifiedPacket, null, 2)}</pre>
      )}
    </div>
  );
};

export default ICMP;