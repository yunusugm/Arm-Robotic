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

for (let i = 0; i < inputSlider.length; i++) {
  const input = inputSlider[i];
  const slide = slideValue[i];

  input.oninput = () => {
    let value = input.value;
    slide.textContent = value;
    slide.style.left = value / 2 + "%";
    slide.classList.add("show");
  };

  input.onblur = () => {
    slide.classList.remove("show");
  };
}
