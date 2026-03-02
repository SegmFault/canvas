import express from 'express';
import { createServer } from 'http';
import { Server } from 'socket.io';
import { fileURLToPath } from 'url';
import { dirname, join } from 'path';

const app = express();
const port = 3000;
const server = createServer(app);
const io = new Server(server);  // create a pipe or webscoket
const __dirname = dirname(fileURLToPath(import.meta.url));

app.get('/', (req, res) => {
    res.sendFile(join(__dirname, 'public/index.html'));
});

app.listen(port, () => console.log(`Server running on ${__dirname}:${port}`));
