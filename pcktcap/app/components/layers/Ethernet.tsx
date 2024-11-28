"use client";

import React, { useState } from 'react';
import IPv4 from './IPv4';
import ARP from './ARP';

const Ethernet = ({ packet }: { packet: any }) => {
  const [isOpen, setIsOpen] = useState(false);
  const toggleOpen = () => setIsOpen(!isOpen);

  const nextLayer = packet.nextLayer;
  let NextLayerComponent = null;

  if (nextLayer) {
    switch (nextLayer.layerType) {
      case 'ARP':
        NextLayerComponent = ARP;
        break;
      case 'IPv4':
        NextLayerComponent = IPv4;
        break;
      default:
        NextLayerComponent = null;
    }
  }

  // Remove _id and nextLayer from display
  const { _id, layerType, timestamp, nextLayer: _, ...thisLayer } = packet;

  // Remove layerType from nextLayer
  const { layerType: nextLayerType, ...nextLayerProps } = nextLayer || {};

  return (
    <div className="border p-4 rounded-lg shadow-md">
      <div onClick={toggleOpen} className="cursor-pointer text-lg">
        <strong>Ethernet Layer</strong>
        <pre className="mt-2 p-2 rounded">{JSON.stringify(thisLayer, null, 2)}</pre>
      </div>
      {nextLayer && (
        <div className="mt-4">
          {NextLayerComponent && <NextLayerComponent packet={nextLayerProps} />}
        </div>
      )}
    </div>
  );
};

export default Ethernet;