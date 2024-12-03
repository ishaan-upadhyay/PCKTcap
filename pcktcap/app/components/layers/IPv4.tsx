import React, { useState } from 'react';
import ICMP from './ICMP';
import UDP from './UDP';
import TCP from './TCP';

const IPv4 = ({ packet }: { packet: any }) => {
  const [isOpen, setIsOpen] = useState(false);
  const toggleOpen = () => setIsOpen(!isOpen);

  // Decompose the packet into itself and nextLayer,
  // so nextLayer isn't displayed at this layer
  const { nextLayer, ...restPacket } = packet;

  // Decompose nextLayer into layerType (rename to nextLayerType)
  // and restNextLayer.
  const { layerType: nextLayerType, ...restNextLayer } = nextLayer || {};

  let NextLayerComponent = null;

  if (restNextLayer) {
    switch (nextLayerType) {
      case 'ICMP':
        NextLayerComponent = ICMP;
        break;
      case 'UDP': // Add this case
        NextLayerComponent = UDP;
        break;
      case 'TCP': // Add this case
        NextLayerComponent = TCP;
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
        <pre className="mt-2 p-2 rounded">{JSON.stringify(restPacket, null, 2)}</pre>
      )}
      {nextLayer && (
        <div className="mt-4">
          {NextLayerComponent && <NextLayerComponent packet={restNextLayer} />}
        </div>
      )}
    </div>
  );
};

export default IPv4;