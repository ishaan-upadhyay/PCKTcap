"use client";

import React, { useState } from 'react';

const ARP = ({ packet }: { packet: any }) => {
  const [isOpen, setIsOpen] = useState(false);
  const toggleOpen = () => setIsOpen(!isOpen);

  return (
    <div>
      <div onClick={toggleOpen} style={{ cursor: 'pointer' }}>
        <strong>ARP Layer</strong>
      </div>
      {isOpen && (
        <div>
            <pre>{JSON.stringify(packet, null, 2)}</pre>
        </div>
      )}
    </div>
  );
};

export default ARP;