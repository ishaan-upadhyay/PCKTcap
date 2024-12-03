import React, { useState } from 'react';
import DNS from './DNS';

const UDP = ({ packet }: { packet: any }) => {
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
      case 'DNS':
        NextLayerComponent = DNS;
        break;
    }
  }

  return (
    <div className="border p-4 rounded-lg shadow-md">
      <div onClick={toggleOpen} className="cursor-pointer font-bold text-lg">
        <strong>UDP Layer</strong>
      </div>
      {isOpen && (
        <div>
          <pre className="mt-2 p-2 rounded">{JSON.stringify(restPacket, null, 2)}</pre>
        </div>
      )}
      {nextLayer && (
        <div className="mt-4">
          {NextLayerComponent && <NextLayerComponent packet={restNextLayer} />}
        </div>
      )}
    </div>
  );
};

export default UDP;