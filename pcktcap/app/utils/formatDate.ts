const formatDate = (collection: string) => {
    const timestamp = collection.split('_')[1];
    const date = new Date(parseInt(timestamp) * 1000); // Convert seconds to milliseconds
    return date.toLocaleString();
};

export { formatDate };