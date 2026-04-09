/* Must run before xterm.js initialises. Ensures the WebGL canvas retains its
   pixel buffer so the bloom canvas can readback pixels via drawImage(). */
const _origGetContext = HTMLCanvasElement.prototype.getContext;
HTMLCanvasElement.prototype.getContext = function (
  this: HTMLCanvasElement,
  type: string,
  attrs?: Record<string, unknown>
): RenderingContext | null {
  if (type === 'webgl' || type === 'webgl2') {
    attrs = Object.assign({}, attrs ?? {}, { preserveDrawingBuffer: true });
  }
  return (_origGetContext as Function).call(this, type, attrs);
} as typeof HTMLCanvasElement.prototype.getContext;
