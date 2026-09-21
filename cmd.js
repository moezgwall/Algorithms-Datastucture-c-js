const { spawn } = require("child_process");

const spawnOptions = {
  shell: true,
  // cwd: process.cwd(),
  // env: process.env,
  // stdio: 'pipe',
};

function cmd(prog, args) {
  console.log("CMD:", prog, args.flat(), spawnOptions);
  const p = spawn(prog, args.flat(), spawnOptions);
  p.stdout.on("data", (data) => process.stdout.write(data));
  p.stderr.on("data", (data) => process.stderr.write(data));
  p.on("close", (code) => {
    if (code !== 0) {
      console.error(prog, args, `exited with ${code}`);
    }
  });
  return p;
}
// testing
cmd("tsx", ["normError.a.ts"]);
