const firebaseConfig = {
  apiKey: "AIzaSyBo-XNbeCo-Wi5nSEur740YSbFGQQxU3NU",
  authDomain: "armfix-b84a8.firebaseapp.com",
  databaseURL: "https://armfix-b84a8-default-rtdb.firebaseio.com",
  projectId: "armfix-b84a8",
  storageBucket: "armfix-b84a8.appspot.com",
  messagingSenderId: "346453177882",
  appId: "1:346453177882:web:aec16f20f737415c6d43a3",
  measurementId: "G-N5TR64F8Y5",
};
// Initialize Firebase
firebase.initializeApp(firebaseConfig);

const slideValue = document.querySelectorAll(
  "#val1, #val2, #val3, #val4, #val5"
);
const inputSlider = document.querySelectorAll(
  "#inVal1, #inVal2, #inVal3, #inVal4, #inVal5"
);
// inputSlider.oninput = () => {
//   let value = inputSlider.value;
//   slideValue.textContent = value;
//   slideValue.style.left = value / 2 + "%";
//   slideValue.classList.add("show");
// };
// inputSlider.onblur = () => {
//   slideValue.classList.remove("show");
// };

console.log(slideValue);
console.log(inputSlider);

for (let i = 0; i < inputSlider.length; i++) {
  const input = inputSlider[i];
  const slide = slideValue[i];

  input.oninput = () => {
    let value = input.value;
    slide.textContent = value;

    slide.style.left = value / 2 + "%";

    slide.classList.add("show");
  };

  // input.onblur = () => {
  //   slide.classList.remove("show");
  // };

  document.addEventListener("click", () => {
    slide.classList.remove("show");
  });
}

const task1 = document.getElementById("task1");
const task2 = document.getElementById("task2");
const task3 = document.getElementById("task3");
const task4 = document.getElementById("task4");
const reset = document.getElementById("reset");

const base = document.getElementById("inVal1");
const shoulder = document.getElementById("inVal2");
const elbow = document.getElementById("inVal3");
const wrist = document.getElementById("inVal4");
const grip = document.getElementById("inVal5");

const baseText = document.getElementById("baseN");
const shoulderText = document.getElementById("shoulderN");
const elbowText = document.getElementById("elbowN");
const wristText = document.getElementById("wristN");
const gripText = document.getElementById("gripN");

const manual = document.getElementById("manual");
const auto = document.getElementById("auto");

const connectFirebase = () => {
  let db = firebase.database();
  let angleRef = "angle/";
  let modeRef = "mode/";
  let taskRef = db.ref(modeRef).child("task");

  reset.addEventListener("click", () => {
    taskRef.set(0);
    console.log("mode 0");
  });

  task1.addEventListener("click", () => {
    taskRef.set(1);
    console.log("mode 1");
  });

  task2.addEventListener("click", () => {
    taskRef.set(2);
    console.log("mode 2");
  });

  task3.addEventListener("click", () => {
    taskRef.set(3);
    console.log("mode 3");
  });

  task4.addEventListener("click", () => {
    taskRef.set(4);
    console.log("mode 4");
  });

  base.addEventListener("input", () => {
    let baseVal = base.value;
    let ref = db.ref(angleRef).child("base");
    ref.set(parseInt(baseVal));
    console.log(`base val ${baseVal}`);
  });

  shoulder.addEventListener("input", () => {
    let shoulderVal = shoulder.value;
    let ref = db.ref(angleRef).child("shoulder");
    ref.set(parseInt((shoulderVal - 180) * -1));
    console.log(`shoulder val ${shoulderVal}`);
  });

  elbow.addEventListener("input", () => {
    let elbowVal = elbow.value;
    let ref = db.ref(angleRef).child("elbow");
    ref.set(parseInt(elbowVal));
    console.log(`elbow val ${elbowVal}`);
  });

  wrist.addEventListener("input", () => {
    let wristVal = wrist.value;
    let ref = db.ref(angleRef).child("wrist");
    ref.set(parseInt(wristVal));
    console.log(`wrist val ${wristVal}`);
  });

  grip.addEventListener("input", () => {
    let gripVal = grip.value;
    let ref = db.ref(angleRef).child("grip");
    ref.set(parseInt(gripVal));
    console.log(`grip val ${gripVal}`);
  });

  manual.addEventListener("click", () => {
    let ref = db.ref(modeRef).child("arm");
    ref.set(0);
  });

  auto.addEventListener("click", () => {
    let ref = db.ref(modeRef).child("arm");
    ref.set(1);
  });

  db.ref(angleRef)
    .child("base")
    .on("value", (snap) => {
      baseText.innerHTML = "";
      baseText.innerHTML += `Base: ${snap.val()} deg`;
    });

  db.ref(angleRef)
    .child("grip")
    .on("value", (snap) => {
      gripText.innerHTML = "";
      gripText.innerHTML += `Grip: ${snap.val()} deg`;
    });

  db.ref(angleRef)
    .child("shoulder")
    .on("value", (snap) => {
      shoulderText.innerHTML = "";
      shoulderText.innerHTML += `Shoulder: ${snap.val()} deg`;
    });

  db.ref(angleRef)
    .child("elbow")
    .on("value", (snap) => {
      elbowText.innerHTML = "";
      elbowText.innerHTML += `Elbow: ${snap.val()} deg`;
    });

  db.ref(angleRef)
    .child("wrist")
    .on("value", (snap) => {
      wristText.innerHTML = "";
      wristText.innerHTML += `Wrist: ${snap.val()} deg`;
    });
};

document.addEventListener("DOMContentLoaded", connectFirebase);
