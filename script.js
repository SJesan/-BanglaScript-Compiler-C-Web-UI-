document.getElementById('compile-form').addEventListener('submit', async function(e) {
  e.preventDefault();
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
}); 