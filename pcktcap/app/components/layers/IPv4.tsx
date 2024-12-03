import React, { useState } from 'react';
import ICMP from './ICMP';
import UDP from './UDP';
import TCP from './TCP';

const IPv4 = ({ packet }: { packet: any }) => {
  const [isOpen, setIsOpen] = useState(false);
  const toggleOpen = () => setIsOpen(!isOpen);

  const flags = packet.flags;
  
  const flagNames: { [key: number]: string } = {
    0x01: 'Reserved',
    0x02: 'Don\'t Fragment',
    0x04: 'More Fragments'
  };
  
  const parsedFlags = Object.keys(flagNames)
    .filter(flag => flags & parseInt(flag))
    .map(flag => flagNames[parseInt(flag)]);

  const modifiedPacket = { 
    ...packet, 
    flags: parsedFlags,
    ipHeaderLength: `${packet.ipHeaderLength} (${packet.ipHeaderLength * 4} bytes)`
  };

  // Decompose the packet into itself and nextLayer,
  // so nextLayer isn't displayed at this layer
  const { nextLayer, ...restPacket } = modifiedPacket;

  // Decompose nextLayer into layerType (rename to nextLayerType)
  // and restNextLayer.
  const { layerType: nextLayerType, ...restNextLayer } = nextLayer || {};

  let NextLayerComponent = null;

  if (restNextLayer) {
    switch (nextLayerType) {
      case 'ICMP':
        NextLayerComponent = ICMP;
        break;
      case 'UDP':
        NextLayerComponent = UDP;
        break;
      case 'TCP':
        NextLayerComponent = TCP;
        break;
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