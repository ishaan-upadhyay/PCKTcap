import React, { useState } from 'react';
import ICMP from './ICMP';

const IPv4 = ({ packet }: { packet: any }) => {
  const [isOpen, setIsOpen] = useState(false);
  const toggleOpen = () => setIsOpen(!isOpen);

  const nextLayer = packet.nextLayer;
  let NextLayerComponent = null;

  if (nextLayer) {
    switch (nextLayer.layerType) {
      case 'ICMP':
        NextLayerComponent = ICMP;
        break;
      // ...existing code...
    }
  }

  return (
    <div className="border p-4 rounded-lg shadow-md">
      <div onClick={toggleOpen} className="cursor-pointer font-bold text-lg">
        <strong>IPv4 Layer</strong>
      </div>
      {isOpen && (
        <pre className="mt-2 p-2 rounded">{JSON.stringify(packet, null, 2)}</pre>
      )}
      {nextLayer && (
        <div className="mt-4">
          {NextLayerComponent && <NextLayerComponent packet={nextLayer} />}
        </div>
      )}
    </div>
  );
};

export default IPv4;