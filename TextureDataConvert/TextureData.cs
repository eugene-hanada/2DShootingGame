using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace TextureDataConvert
{
	/// <summary> テクスチャデータ用クラス </summary>
	internal class TextureData
	{
		/// <summary> 画像上の座標 </summary>
		private Vector2 pos_;

		/// <summary>  </summary>
		private Vector2 wh_;

		private int num_;

		public TextureData(XElement? sprite, int num)
		{
			if (sprite == null)
			{
				throw new ArgumentNullException(nameof(sprite));
			}

			var x = sprite.Attribute("x");
			var y = sprite.Attribute("y");
			if (x == null || y == null)
			{
				throw new ArgumentNullException("xもしくはyの値がありません");
			}
			pos_ = new Vector2(float.Parse(x.Value), float.Parse(y.Value));

			var w = sprite.Attribute("w");
			var h = sprite.Attribute("h");

			if (w == null || h == null)
			{
				throw new ArgumentNullException("wもしくはhの値がありません");
			}
			wh_ = new Vector2(float.Parse(w.Value), float.Parse(h.Value));

			this.num_ = num;
		}

		public void Write(BinaryWriter bw)
		{
			pos_.Write(bw);
			wh_.Write(bw);
		}

		public int GetNum()
		{
			return num_;
		}

		public Vector2 GetPos()
        {
			return pos_;
        }

		public Vector2 GetWH()
        {
			return wh_;
        }


	}
}
