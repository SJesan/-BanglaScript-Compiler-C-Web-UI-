document.getElementById('compileBtn').onclick = async function() {
  const code = document.getElementById('code').value;
  const output = document.getElementById('output');
  output.textContent = 'Compiling...';
  try {
    const res = await fetch('/compile', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ code })
    });
    const text = await res.text();
    output.textContent = text;
  } catch (err) {
    output.textContent = 'Error: ' + err;
  }
}; 