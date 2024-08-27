import * as THREE from "three";
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls";

// Assume we have a WASM module with our physics calculations
import Module from "./build/physicsSim.wasm";

let scene, camera, renderer, controls;
let balls = [];
const numBalls = 5;
const ballRadius = 0.5;
const ballSpacing = 0.1;
const stringLength = 5;

function init() {
  // Set up Three.js scene
  scene = new THREE.Scene();
  camera = new THREE.PerspectiveCamera(
    75,
    window.innerWidth / window.innerHeight,
    0.1,
    1000
  );
  renderer = new THREE.WebGLRenderer();
  renderer.setSize(window.innerWidth, window.innerHeight);
  document.body.appendChild(renderer.domElement);

  // Add lights
  const ambientLight = new THREE.AmbientLight(0x404040);
  scene.add(ambientLight);
  const directionalLight = new THREE.DirectionalLight(0xffffff, 0.5);
  directionalLight.position.set(1, 1, 1);
  scene.add(directionalLight);

  // Set up camera and controls
  camera.position.set(0, 0, 15);
  controls = new OrbitControls(camera, renderer.domElement);

  // Create balls
  const ballGeometry = new THREE.SphereGeometry(ballRadius, 32, 32);
  const ballMaterial = new THREE.MeshPhongMaterial({ color: 0x888888 });

  for (let i = 0; i < numBalls; i++) {
    const ball = new THREE.Mesh(ballGeometry, ballMaterial);
    ball.position.set(
      (i - (numBalls - 1) / 2) * (ballRadius * 2 + ballSpacing),
      -stringLength,
      0
    );
    scene.add(ball);
    balls.push(ball);

    // Create string
    const stringGeometry = new THREE.BufferGeometry();
    const stringMaterial = new THREE.LineBasicMaterial({ color: 0xffffff });
    const stringPoints = [
      new THREE.Vector3(ball.position.x, 0, 0),
      ball.position,
    ];
    stringGeometry.setFromPoints(stringPoints);
    const string = new THREE.Line(stringGeometry, stringMaterial);
    scene.add(string);
    ball.string = string;
  }

  // Initialize WASM module
  Module.onRuntimeInitialized = () => {
    // Create Ball objects in WASM
    balls.forEach((ball, index) => {
      const mass = 1;
      const pos = ball.position;
      const vel = new THREE.Vector3(0, 0, 0);
      ball.physicsObject = new Module.Ball(
        mass,
        ballRadius,
        pos.x,
        pos.y,
        pos.z,
        vel.x,
        vel.y,
        vel.z
      );
    });

    // Start animation
    animate();
  };
}

function updatePhysics(dt) {
  const gravity = 9.81;

  balls.forEach((ball, index) => {
    ball.physicsObject.updatePendulum(dt, stringLength, gravity);

    // Update Three.js object position
    const newPos = ball.physicsObject.getPosition();
    ball.position.set(newPos.x, newPos.y, newPos.z);

    // Update string
    ball.string.geometry.setFromPoints([
      new THREE.Vector3(ball.position.x, 0, 0),
      ball.position,
    ]);
    ball.string.geometry.verticesNeedUpdate = true;
  });

  // Check for collisions
  for (let i = 0; i < balls.length - 1; i++) {
    for (let j = i + 1; j < balls.length; j++) {
      if (balls[i].physicsObject.isColliding(balls[j].physicsObject)) {
        balls[i].physicsObject.handleCollision(balls[j].physicsObject);
      }
    }
  }
}

function animate() {
  requestAnimationFrame(animate);

  const dt = 1 / 60; // Assume 60 FPS
  updatePhysics(dt);

  controls.update();
  renderer.render(scene, camera);
}

init();
