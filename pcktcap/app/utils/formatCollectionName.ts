const formatCollectionName = (collection: string) => {
    const parts = collection.split('_');
    const date = new Date(parseInt(parts[1]) * 1000); // Convert seconds to milliseconds
    return date.toLocaleString() + ' on interface ' + parts[2];
};

export { formatCollectionName };