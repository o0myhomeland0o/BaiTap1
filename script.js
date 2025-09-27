// helper
function isLetter(c){ return /[A-Za-z]/.test(c); }
function up(c){ return c.toUpperCase(); }

// UI params
const paramsDiv = document.getElementById('params');
function renderParams(){
  const cipher = document.getElementById('cipher').value;
  let html='';
  if(cipher==='caesar'){
    html = `<label>Key (number)</label><input id="p_key" type="text" value="3">`;
  } else if(cipher==='affine'){
    html = `<label>Key (a,b)</label><input id="p_key" type="text" value="5,8">`;
  } else if(cipher==='columnar'){
    html = `<label>Key (word)</label><input id="p_key" type="text" value="SECRET">`;
  } else if(cipher==='vigenere'){
    html = `<label>Key (word)</label><input id="p_key" type="text" value="KEY">`;
  } else if(cipher==='playfair'){
    html = `<label>Key (word)</label><input id="p_key" type="text" value="PLAYFAIR">`;
  }
  paramsDiv.innerHTML = html;
}
document.getElementById('cipher').addEventListener('change', renderParams);
renderParams();

// Caesar
function caesarEncrypt(s,k){
  k = ((k%26)+26)%26;
  let out = '';
  for(const ch of s){
    if(ch>='A' && ch<='Z') out += String.fromCharCode('A'.charCodeAt(0) + (ch.charCodeAt(0)-'A'.charCodeAt(0)+k)%26);
    else if(ch>='a' && ch<='z') out += String.fromCharCode('a'.charCodeAt(0) + (ch.charCodeAt(0)-'a'.charCodeAt(0)+k)%26);
    else out += ch;
  }
  return out;
}
function caesarDecrypt(s,k){ return caesarEncrypt(s, -k); }

// Affine
function egcd(a,b){ if(b===0) return [1,0,a]; let r=egcd(b, a%b); return [r[1], r[0]-Math.floor(a/b)*r[1], r[2]]; }
function modinv(a,m){ let r=egcd(a,m); if(r[2]!==1) return null; let x=r[0]%m; if(x<0) x+=m; return x; }
function affineEncrypt(s,a,b){
  let out='';
  for(const ch of s){
    if(isLetter(ch)){
      const base = (ch===ch.toUpperCase()? 'A'.charCodeAt(0) : 'a'.charCodeAt(0));
      const x = ch.charCodeAt(0)-base;
      out += String.fromCharCode(base + (a*x + b)%26);
    } else out += ch;
  }
  return out;
}
function affineDecrypt(s,a,b){
  const ainv = modinv(a,26);
  if(ainv===null) return '[a not invertible mod26]';
  let out='';
  for(const ch of s){
    if(isLetter(ch)){
      const base = (ch===ch.toUpperCase()? 'A'.charCodeAt(0) : 'a'.charCodeAt(0));
      const y = ch.charCodeAt(0)-base;
      out += String.fromCharCode(base + ( (ainv*(y - b + 26*10))%26 ));
    } else out += ch;
  }
  return out;
}

// Columnar
function sanitizeAlpha(s){ return s.replace(/[^A-Za-z]/g,'').toUpperCase(); }
function columnarEncrypt(pt,key){
  const s = sanitizeAlpha(pt);
  if(!key) return s;
  const k = key.length;
  const rows = Math.ceil(s.length / k);
  let padded = s;
  while(padded.length < rows*k) padded += 'X';
  const cols = [];
  for(let c=0;c<k;c++){ cols[c]=''; for(let r=0;r<rows;r++) cols[c]+=padded[r*k+c]; }
  const arr = [];
  for(let i=0;i<k;i++) arr.push([key[i].toUpperCase(), i]);
  arr.sort();
  let ct='';
  for(const a of arr) ct += cols[a[1]];
  return ct;
}
function columnarDecrypt(ct,key){
  const s = sanitizeAlpha(ct);
  const k = key.length;
  const rows = s.length / k;
  const arr = [];
  for(let i=0;i<k;i++) arr.push([key[i].toUpperCase(), i]);
  arr.sort();
  const cols = new Array(k);
  let idx=0;
  for(const a of arr){
    cols[a[1]] = s.substr(idx, rows);
    idx += rows;
  }
  let pt='';
  for(let r=0;r<rows;r++) for(let c=0;c<k;c++) pt+=cols[c][r];
  return pt;
}

// Vigenere
function vigenereEncrypt(pt,key){
  let k = key.replace(/[^A-Za-z]/g,'').toUpperCase();
  if(k.length===0) return pt;
  let out=''; let j=0;
  for(const ch of pt){
    if(isLetter(ch)){
      const base = (ch===ch.toUpperCase()? 'A'.charCodeAt(0) : 'a'.charCodeAt(0));
      const ki = k[j % k.length].charCodeAt(0)-'A'.charCodeAt(0);
      const x = ch.charCodeAt(0)-base;
      out += String.fromCharCode(base + (x+ki)%26);
      j++;
    } else out += ch;
  }
  return out;
}
function vigenereDecrypt(ct,key){
  let k = key.replace(/[^A-Za-z]/g,'').toUpperCase();
  if(k.length===0) return ct;
  let out=''; let j=0;
  for(const ch of ct){
    if(isLetter(ch)){
      const base = (ch===ch.toUpperCase()? 'A'.charCodeAt(0) : 'a'.charCodeAt(0));
      const ki = k[j % k.length].charCodeAt(0)-'A'.charCodeAt(0);
      const y = ch.charCodeAt(0)-base;
      out += String.fromCharCode(base + (y - ki + 26)%26);
      j++;
    } else out += ch;
  }
  return out;
}

// Playfair
function buildPlayMat(key){
  let p = key.replace(/[^A-Za-z]/g,'').toUpperCase().replace(/J/g,'I');
  let used = new Array(26).fill(false);
  used['J'.charCodeAt(0)-'A'.charCodeAt(0)] = true;
  const seq = [];
  for(const ch of p){ const idx=ch.charCodeAt(0)-'A'.charCodeAt(0); if(!used[idx]){ seq.push(ch); used[idx]=true; } }
  for(let i=0;i<26;i++){
    if(!used[i]) seq.push(String.fromCharCode('A'.charCodeAt(0)+i));
  }
  const mat = [];
  for(let r=0;r<5;r++) mat.push(seq.slice(5*r, 5*r+5));
  return mat;
}
function findPos(mat, ch){
  for(let r=0;r<5;r++) for(let c=0;c<5;c++) if(mat[r][c]===ch) return [r,c];
  return [-1,-1];
}
function playfairPrepare(s){
  let t = s.replace(/[^A-Za-z]/g,'').toUpperCase().replace(/J/g,'I');
  const pairs=[];
  for(let i=0;i<t.length;){
    const a = t[i];
    const b = (i+1<t.length? t[i+1] : 'X');
    if(a===b){ pairs.push([a,'X']); i+=1; }
    else { pairs.push([a,b]); i+=2; }
  }
  if(pairs.length>0){
    const last = pairs[pairs.length-1];
    if(last[1]===undefined) last[1]='X';
  }
  return pairs;
}
function playfairEncrypt(pt,key){
  const mat = buildPlayMat(key);
  const pairs = playfairPrepare(pt);
  let out='';
  for(const p of pairs){
    const a=p[0], b=p[1];
    const pa=findPos(mat,a), pb=findPos(mat,b);
    const ra=pa[0], ca=pa[1], rb=pb[0], cb=pb[1];
    if(ra===rb){
      out += mat[ra][(ca+1)%5];
      out += mat[rb][(cb+1)%5];
    } else if(ca===cb){
      out += mat[(ra+1)%5][ca];
      out += mat[(rb+1)%5][cb];
    } else {
      out += mat[ra][cb];
      out += mat[rb][ca];
    }
  }
  return out;
}
function playfairDecrypt(ct,key){
  const mat = buildPlayMat(key);
  const s = ct.replace(/[^A-Za-z]/g,'').toUpperCase();
  let out='';
  for(let i=0;i<s.length; i+=2){
    const a=s[i], b=s[i+1];
    const pa=findPos(mat,a), pb=findPos(mat,b);
    const ra=pa[0], ca=pa[1], rb=pb[0], cb=pb[1];
    if(ra===rb){
      out += mat[ra][(ca+5-1)%5];
      out += mat[rb][(cb+5-1)%5];
    } else if(ca===cb){
      out += mat[(ra+5-1)%5][ca];
      out += mat[(rb+5-1)%5][cb];
    } else {
      out += mat[ra][cb];
      out += mat[rb][ca];
    }
  }
  return out;
}

// Main actions
function doEnc(){
  const cipher = document.getElementById('cipher').value;
  const key = document.getElementById('p_key').value;
  const input = document.getElementById('input').value;
  let out='';
  if(cipher==='caesar') out = caesarEncrypt(input, parseInt(key||0));
  else if(cipher==='affine'){
    const parts = key.split(',').map(x=>parseInt(x.trim()));
    if(parts.length<2) out='Enter a,b';
    else out = affineEncrypt(input, parts[0], parts[1]);
  } else if(cipher==='columnar') out = columnarEncrypt(input, key);
  else if(cipher==='vigenere') out = vigenereEncrypt(input, key);
  else if(cipher==='playfair') out = playfairEncrypt(input, key);
  document.getElementById('output').textContent = out;
}
function doDec(){
  const cipher = document.getElementById('cipher').value;
  const key = document.getElementById('p_key').value;
  const input = document.getElementById('input').value;
  let out='';
  if(cipher==='caesar') out = caesarDecrypt(input, parseInt(key||0));
  else if(cipher==='affine'){
    const parts = key.split(',').map(x=>parseInt(x.trim()));
    if(parts.length<2) out='Enter a,b';
    else out = affineDecrypt(input, parts[0], parts[1]);
  } else if(cipher==='columnar') out = columnarDecrypt(input, key);
  else if(cipher==='vigenere') out = vigenereDecrypt(input, key);
  else if(cipher==='playfair') out = playfairDecrypt(input, key);
  document.getElementById('output').textContent = out;
}
