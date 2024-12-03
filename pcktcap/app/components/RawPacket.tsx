"use client";

import { useState } from 'react';

const RawPacket = ({ raw }: { raw: string }) => {
  const [showRaw, setShowRaw] = useState(false);

  return (
    <div className="border p-4 rounded-lg shadow-md">
      <button onClick={() => setShowRaw(!showRaw)} className="text-blue-500">
        {showRaw ? 'Hide raw packet' : 'Show raw packet'}
      </button>
      {showRaw && <p className="p-2 mt-2 break-words">{raw}</p>}
    </div>
  );
};

export default RawPacket;
