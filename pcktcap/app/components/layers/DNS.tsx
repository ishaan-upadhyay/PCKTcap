import React, { useState } from 'react';

const DNS = ({ packet }: { packet: any }) => {
  const [isOpen, setIsOpen] = useState(false);
  const toggleOpen = () => setIsOpen(!isOpen);

  return (
    <div className="border p-4 rounded-lg shadow-md">
      <div onClick={toggleOpen} className="cursor-pointer font-bold text-lg">
        <strong>DNS Layer</strong>
      </div>
      {isOpen && (
        <pre className="mt-2 p-2 rounded">{JSON.stringify(packet, null, 2)}</pre>
      )}
    </div>
  );
};

export default DNS;