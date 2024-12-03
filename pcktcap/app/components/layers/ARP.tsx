"use client";

import React, { useState } from 'react';

const ARP = ({ packet }: { packet: any }) => {
  const [isOpen, setIsOpen] = useState(false);
  const toggleOpen = () => setIsOpen(!isOpen);

  const hardwareTypes: { [key: number]: string } = {
    1: 'Ethernet'
  };

  const protocolTypes: { [key: number]: string } = {
    0x0800: 'IPv4'
  };

  const opcodes: { [key: number]: string } = {
    1: 'Request',
    2: 'Reply'
  };

  const modifiedPacket = {
    ...packet,
    hardwareType: `${packet.hardwareType} (${hardwareTypes[packet.hardwareType] || 'Unknown'})`,
    protocolType: `${packet.protocolType} (${protocolTypes[packet.protocolType] || 'Unknown'})`,
    opcode: `${packet.opcode} (${opcodes[packet.opcode] || 'Unknown'})`
  };

  return (
    <div className="border p-4 rounded-lg shadow-md">
      <div onClick={toggleOpen} className="cursor-pointer font-bold text-lg">
        <strong>ARP Layer</strong>
      </div>
      {isOpen && (
        <pre className="mt-2 p-2 rounded">{JSON.stringify(modifiedPacket, null, 2)}</pre>
      )}
    </div>
  );
};

export default ARP;