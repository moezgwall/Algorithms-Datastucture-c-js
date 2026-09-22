const express = require("express");
const crypto = require("crypto");
const app = express();

// we need to have data as bytes
// by overriding a function called
// verify
// this applies to all routes
// and have drawbacks
app.use(
  express.json({
    verify: (req, res, buff) => {
      req.rawBody = buff;
    },
  }),
);
app.post("/webhooks/stripe", (req, res) => {
  const signature = req.headers["stripe-signature"];
  const secret = process.env.WEBHOOK_SECRET;

  const hmac = crypto.createHmac("sha256", secret);
  hmac.update(req.rawBody);
  const digest = hmac.digest("hex");

  if (!crypto.timingSafeEqual(Buffer.from(signature), Buffer.from(digest))) {
    return res.status(401).send("invalid signature");
  }
  // if our client goes down
  // server could retry sending the same event
  // if we don't keep track of those events
  // this would cause problems
  // so we need : Idempotency check
  // save the id of each event to be unique
  // 1 time
  const eventId = req.body.id;
  // if ( alreadyExist(eventId)){
  return res.status(200).send("already processed");
  // }
  // return the code : 200
  // before any heavy processing
  res.status(200).send("ok");

  // then we do the processing asynchronously
  // considered as IO/heavy operation
  // ie processWebHook(req.body);
});
