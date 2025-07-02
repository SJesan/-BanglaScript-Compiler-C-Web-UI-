const express = require('express');
const path = require('path');
const { spawn } = require('child_process');
const app = express();
const PORT = 3000;

// Serve static files from the root directory
app.use(express.static(__dirname));
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// POST /compile: receive code, run C++ compiler, return output
app.post('/compile', (req, res) => {
    const code = req.body.code;
    if (!code) return res.status(400).send('No code provided');

    // Use Linux binary for Render (no .exe)
    const proc = spawn('./banglascript_compiler', [], { shell: true });

    let output = '';
    proc.stdout.on('data', data => { output += data.toString(); });
    proc.stderr.on('data', data => { output += data.toString(); });

    proc.on('close', () => {
        res.send(output);
    });

    // Send code to the compiler (simulate user input, end with #)
    proc.stdin.write(code + '\n#\n');
    proc.stdin.end();
});

app.listen(PORT, () => {
    console.log(`BanglaScript Web UI running at http://localhost:${PORT}`);
}); 