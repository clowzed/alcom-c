<div style = "font-family: 'Courier New'">
<h1>alcom (C lang)</h1>
</div>


<div style = "font-family: 'Courier New'">
<h1>what is it?</h1>
<h4>This a simple comments aligner for assemblers</h4>
</div>

<div style = "font-family: 'Courier New'">
<h1>demonstration</h1>
<h5>Before aligning</h5>
</div>

```
.386
DATA SEGMENT USE16
MESG DB 'Hello ; word','$' ;     msg
DATA ENDS ;;
CODE SEGMENT USE16
    ASSUME CS:CODE,DS:DATA ;;;
BEG:
    MOV AX,DATA
    MOV DS,AX;
    MOV AH,9
    MOV DX, OFFSET MESG
    INT 21H
    MOV AH,4CH
    INT 21H ;back to dos
CODE ENDS
END BEG
```
<div style = "font-family: 'Courier New'">
<h5>After aligning</h5>
</div>

```
.386
DATA SEGMENT USE16
MESG DB 'Hello word','$'                ;    msg
DATA ENDS
CODE SEGMENT USE16
    ASSUME CS:CODE,DS:DATA
BEG:
    MOV AX,DATA
    MOV DS,AX
    MOV AH,9
    MOV DX, OFFSET MESG
    INT 21H
    MOV AH,4CH
    INT 21H                             ;    back to dos
CODE ENDS
END BEG

```



<div style = "font-family: 'Courier New'">
<h1>requirements</h1>
<ul>
    <li><strong>gcc</strong> of any version</li>
    <li> <strong>make</strong> for building</li>
</ul>
</div>



<div style = "font-family: 'Courier New'">
<h1>installation</h1>
</div>

```bash
git clone https://github.com/clowzed/alcom-c.git
cd alcom-c
make
make install
```

<div style = "font-family: 'Courier New'">
<h1>usage</h1>
</div>

```bash
alcom file1.asm file2.asm file2.asm
```